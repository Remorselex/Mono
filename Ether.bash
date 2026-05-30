#!/bin/bash

PIPE_DOWN=10
PIPE_UP=11
PF_ANCHOR="ether_shaper"
CONFIG_FILE="/tmp/ether_shaper.conf"
PF_CONF_BACKUP="/etc/pf.conf.ether_backup"

check_tools() {
    for tool in pfctl dnctl ifconfig awk; do
        command -v "$tool" &>/dev/null || { echo "❌ Required tool not found: $tool"; exit 1; }
    done
}

setup_anchor() {
    if ! grep -q "\"$PF_ANCHOR\"" /etc/pf.conf 2>/dev/null; then
        sudo cp /etc/pf.conf "$PF_CONF_BACKUP"
        printf '\ndummynet-anchor "%s"\nanchor "%s"\n' "$PF_ANCHOR" "$PF_ANCHOR" | \
            sudo tee -a /etc/pf.conf > /dev/null
        sudo pfctl -f /etc/pf.conf 2>/dev/null
        echo "ℹ️  Anchor added to /etc/pf.conf (backup: $PF_CONF_BACKUP)"
    fi
}

apply_limit() {
    local IFACE="$1"
    local DOWNLOAD="$2"
    local UPLOAD="$3"
    local LATENCY="$4"
    local LOSS="$5"

    echo "Applying limits to $IFACE ..."

    setup_anchor

    local OPTS_DOWN="bw ${DOWNLOAD}Kbit/s"
    local OPTS_UP="bw ${UPLOAD}Kbit/s"

    [[ "${LATENCY:-0}" != "0" ]] && {
        OPTS_DOWN+=" delay $LATENCY"
        OPTS_UP+=" delay $LATENCY"
    }

    if [[ "${LOSS:-0}" != "0" ]]; then
        local PLR
        PLR=$(awk "BEGIN {printf \"%.4f\", $LOSS / 100}")
        OPTS_DOWN+=" plr $PLR"
        OPTS_UP+=" plr $PLR"
    fi

    sudo dnctl pipe $PIPE_DOWN config $OPTS_DOWN
    sudo dnctl pipe $PIPE_UP   config $OPTS_UP

    printf 'dummynet in  on %s all pipe %d\ndummynet out on %s all pipe %d\n' \
        "$IFACE" "$PIPE_DOWN" "$IFACE" "$PIPE_UP" | \
        sudo pfctl -a "$PF_ANCHOR" -f -

    sudo pfctl -e 2>/dev/null || true

    printf 'DOWN=%s\nUP=%s\n' "$DOWNLOAD" "$UPLOAD" > "$CONFIG_FILE"

    echo "✅ Limit applied:"
    echo "  Download: ${DOWNLOAD} kbit/s"
    echo "  Upload:   ${UPLOAD} kbit/s"
    (( LATENCY > 0 ))           && echo "  Latency:  ${LATENCY} ms"
    [[ "${LOSS:-0}" != "0" ]]   && echo "  Loss:     ${LOSS}%"
}

clear_limit() {
    local IFACE="$1"
    echo "Clearing limits from $IFACE ..."

    # Stop all traffic shaping immediately
    sudo pfctl -a "$PF_ANCHOR" -F all 2>/dev/null
    sudo dnctl pipe $PIPE_DOWN delete 2>/dev/null
    sudo dnctl pipe $PIPE_UP   delete 2>/dev/null

    # Restore original pf.conf and reload
    if [[ -f "$PF_CONF_BACKUP" ]]; then
        sudo cp "$PF_CONF_BACKUP" /etc/pf.conf
        sudo pfctl -f /etc/pf.conf 2>/dev/null
        sudo rm -f "$PF_CONF_BACKUP"
        echo "ℹ️  /etc/pf.conf restored"
    fi

    rm -f "$CONFIG_FILE"
    echo "✅ Cleared. All limits removed, factory state restored."
}

reset_netem() {
    if [[ ! -f "$CONFIG_FILE" ]]; then
        echo "ℹ️  No active configuration found."
        return
    fi

    # shellcheck source=/dev/null
    source "$CONFIG_FILE"
    echo "Resetting latency / packet loss ..."

    sudo dnctl pipe $PIPE_DOWN delete 2>/dev/null
    sudo dnctl pipe $PIPE_UP   delete 2>/dev/null

    sudo dnctl pipe $PIPE_DOWN config bw "${DOWN}Kbit/s"
    sudo dnctl pipe $PIPE_UP   config bw "${UP}Kbit/s"

    echo "✅ Latency and packet loss cleared (bandwidth limits kept)."
}

check_existing_limits() {
    if sudo dnctl pipe $PIPE_DOWN show &>/dev/null; then
        echo "⚠️  Active limits detected from a previous session:"
        sudo dnctl pipe $PIPE_DOWN show 2>/dev/null | head -1
        sudo dnctl pipe $PIPE_UP   show 2>/dev/null | head -1
        echo ""
        read -p "Clear them before continuing? [y/N]: " REPLY
        if [[ "$REPLY" =~ ^[Yy]$ ]]; then
            sudo pfctl -a "$PF_ANCHOR" -F all 2>/dev/null
            sudo dnctl pipe $PIPE_DOWN delete 2>/dev/null
            sudo dnctl pipe $PIPE_UP   delete 2>/dev/null
            if [[ -f "$PF_CONF_BACKUP" ]]; then
                sudo cp "$PF_CONF_BACKUP" /etc/pf.conf
                sudo pfctl -f /etc/pf.conf 2>/dev/null
                sudo rm -f "$PF_CONF_BACKUP"
            fi
            rm -f "$CONFIG_FILE"
            echo "✅ Previous limits cleared."
            echo ""
        fi
    fi
}

show_interfaces() {
    echo "--- Available interfaces ---"
    ifconfig -l | tr ' ' '\n' | grep -v "^lo"
    echo "---------------------------"
}

### MAIN ###

clear
echo "=== PF/Dummynet Traffic Shaping Controller ==="
check_tools
check_existing_limits
show_interfaces

read -p "Interface name: " IFACE

if ! ifconfig "$IFACE" &>/dev/null; then
    echo "❌ Interface not found."
    exit 1
fi

echo "1. Set limit"
echo "2. Clear all limits"
echo "3. Reset latency / packet loss"
read -p "Choose action: " ACTION

if [[ "$ACTION" == "1" ]]; then
    read -p "Download (kbit/s): " DOWN
    [[ "$DOWN" =~ ^[0-9]+$ ]] || { echo "❌ Download must be a number"; exit 1; }

    read -p "Upload   (kbit/s) [Enter = same as download]: " UP
    [[ -z "$UP" ]] && UP="$DOWN"
    [[ "$UP" =~ ^[0-9]+$ ]] || { echo "❌ Upload must be a number"; exit 1; }

    read -p "Latency  (ms)     [Enter = 0]: " LATENCY
    LATENCY="${LATENCY:-0}"
    [[ "$LATENCY" =~ ^[0-9]+$ ]] || { echo "❌ Latency must be a number"; exit 1; }

    read -p "Packet loss (%)   [Enter = 0]: " LOSS
    LOSS="${LOSS:-0}"
    [[ "$LOSS" =~ ^[0-9]+([.][0-9]+)?$ ]] || { echo "❌ Loss must be a number"; exit 1; }

    apply_limit "$IFACE" "$DOWN" "$UP" "$LATENCY" "$LOSS"

elif [[ "$ACTION" == "2" ]]; then
    clear_limit "$IFACE"

elif [[ "$ACTION" == "3" ]]; then
    reset_netem

else
    echo "❌ Wrong choice."
fi
