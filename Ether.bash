#!/bin/bash


check_interface_supported() {
    local IFACE="$1"

    if tc qdisc show dev "$IFACE" | grep -q "noqueue"; then
        echo "❌ Interface $IFACE does not support traffic shaping (qdisc noqueue)"
        return 1
    fi

    return 0
}

apply_limit() {
    local IFACE="$1"
    local DOWNLOAD="$2"
    local UPLOAD="$3"

    echo "Applying speed limit to $IFACE ..."

    sudo tc qdisc del dev "$IFACE" root 2>/dev/null

    sudo tc qdisc add dev "$IFACE" root handle 1: htb default 10
    sudo tc class add dev "$IFACE" parent 1: classid 1:1 htb rate "${UPLOAD}kbit"
    sudo tc class add dev "$IFACE" parent 1:1 classid 1:10 htb rate "${DOWNLOAD}kbit"

    sudo tc qdisc add dev "$IFACE" handle ffff: ingress 2>/dev/null
    sudo tc filter add dev "$IFACE" parent ffff: protocol all prio 50 u32 \
         match u32 0 0 police rate "${DOWNLOAD}kbit" burst 10k drop flowid :1

    echo "✅ Limit applied:"
    echo "  Download: ${DOWNLOAD} kbit/s"
    echo "  Upload:   ${UPLOAD} kbit/s"
}

clear_limit() {
    local IFACE="$1"
    echo "Clearing limits from $IFACE ..."

    sudo tc qdisc del dev "$IFACE" root 2>/dev/null
    sudo tc qdisc del dev "$IFACE" ingress 2>/dev/null

    echo "✅ Cleared."
}

show_interfaces() {
    echo "--- Available interfaces ---"
    ip -o link show | awk -F': ' '{print $2}' | grep -v "lo"
    echo "---------------------------"
}

### MAIN ###

clear
echo "=== TC Traffic Shaping Controller ==="
show_interfaces

read -p "Interface name: " IFACE

if ! ip link show "$IFACE" &>/dev/null; then
    echo "❌ Interface not found."
    exit 1
fi

if ! check_interface_supported "$IFACE"; then
    exit 1
fi

echo "1. Set limit"
echo "2. Clear limit"
read -p "Choose action: " ACTION

if [[ "$ACTION" == "1" ]]; then
    read -p "Download (kbit/s): " DOWN
    read -p "Upload   (kbit/s): " UP

    [[ "$DOWN" =~ ^[0-9]+$ ]] || { echo "❌ Download must be a number"; exit 1; }
    [[ "$UP" =~ ^[0-9]+$ ]]   || { echo "❌ Upload must be a number"; exit 1; }

    apply_limit "$IFACE" "$DOWN" "$UP"

elif [[ "$ACTION" == "2" ]]; then
    clear_limit "$IFACE"
else
    echo "❌ Wrong choice."
fi
