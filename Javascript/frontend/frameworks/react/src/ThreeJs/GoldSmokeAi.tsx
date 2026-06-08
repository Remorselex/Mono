import React, { useRef, useMemo } from 'react';
import { Canvas, useFrame, extend,  Object3DNode } from '@react-three/fiber';
import { OrbitControls, shaderMaterial } from '@react-three/drei';
import * as THREE from 'three';
import { Line2 } from 'three/examples/jsm/lines/Line2.js';
import { LineGeometry } from 'three/examples/jsm/lines/LineGeometry.js';
import { LineMaterial } from 'three/examples/jsm/lines/LineMaterial.js';

extend({ Line2, LineGeometry, LineMaterial });

type GoldParticleMaterialType = THREE.ShaderMaterial & {
    uTime: number;
    uSize: number;
};

declare module '@react-three/fiber' {
    interface ThreeElements {
        goldParticleMaterial: Object3DNode<GoldParticleMaterialType, typeof GoldParticleMaterial>;
        line2: Object3DNode<Line2, typeof Line2>;
        lineGeometry: Object3DNode<LineGeometry, typeof LineGeometry>;
        lineMaterial: Object3DNode<LineMaterial, typeof LineMaterial>;
    }
}

// --- ТРАЕКТОРИЯ И ГЕОМЕТРИЯ ВОЛНЫ ---
// Базовая S-образная форма, общая для всего потока
const getBaseWave = (y: number, time: number) => {
    // Частота изгиба подобрана под картинку
    const angle = y * 0.55 + time * 0.3;
    const x = Math.sin(angle) * 1.4;
    const z = Math.cos(angle) * 0.3; // Легкий объем по Z
    return { x, z };
};

// --- ШЕЙДЕР ДЛЯ ЧАСТИЦ (ПЫЛЬ И БОКЕ) ---
const GoldParticleMaterial = shaderMaterial(
    { uTime: 0, uSize: 18.0 },
    /* glsl */ `
    uniform float uTime;
    uniform float uSize;
    attribute float aRandomness;
    attribute float aSpeed;
    attribute float aType; // 0 = мелкая пыль, 1 = крупные боке на фоне
    
    varying vec3 vPosition;
    varying float vRandomness;
    varying float vType;

    float hash(float n) { return fract(sin(n) * 43758.5453123); }

    void main() {
      vec3 pos = position;
      vType = aType;
      vRandomness = aRandomness;

      // Анимация бесконечного подъема вверх
      float progress = uTime * 0.12 * aSpeed;
      pos.y = mod(pos.y + progress + 4.0, 8.0) - 4.0;

      // Базовая S-кривая
      float angle = pos.y * 0.55 + uTime * 0.3;
      vec3 wavePos = vec3(sin(angle) * 1.4, pos.y, cos(angle) * 0.3);

      if (aType < 0.5) {
        // Мелкая золотая пыль: плотно прижата к линиям
        float radius = 0.15 + pow(aRandomness, 2.0) * 0.45;
        float randAngle = aRandomness * 6.28318;
        
        pos.x = wavePos.x + sin(randAngle) * radius;
        pos.z = wavePos.z + cos(randAngle) * radius * 0.5;
        pos.y = wavePos.y;
      } else {
        // Крупные фоновые боке: летают хаотично по всей сцене
        pos.x += sin(aRandomness * 200.0) * 2.5;
        pos.z += cos(aRandomness * 150.0) * 1.5 - 1.0; // Сдвинуты назад
      }

      vec4 mvPosition = modelViewMatrix * vec4(pos, 1.0);
      gl_Position = projectionMatrix * mvPosition;
      
      // Размер: боке делаем огромными, пыль — аккуратной
      float sizeMultiplier = (aType > 0.5) ? (3.5 + hash(aRandomness) * 4.0) : (0.5 + hash(aRandomness) * 1.0);
      gl_PointSize = uSize * sizeMultiplier * (1.0 / -mvPosition.z);
      
      vPosition = pos;
    }
  `,
    /* glsl */ `
    varying vec3 vPosition;
    varying float vRandomness;
    varying float vType;

    void main() {
      float distanceToCenter = length(gl_PointCoord - vec2(0.5));
      if (distanceToCenter > 0.5) discard;
      
      // Разная мягкость краев для пыли и боке
      float power = (vType > 0.5) ? 3.0 : 1.5; 
      float strength = 1.0 - (distanceToCenter * 2.0);
      strength = pow(strength, power);
      
      // Цветовая палитра точь-в-точь как на генерации
      vec3 darkGold = vec3(0.75, 0.42, 0.08);
      vec3 coreGold = vec3(1.0, 0.78, 0.35);
      vec3 whiteHot = vec3(1.0, 0.98, 0.85);
      
      vec3 color = mix(darkGold, coreGold, vRandomness);
      if (vRandomness > 0.85) {
        color = mix(color, whiteHot, (vRandomness - 0.85) * 6.6);
      }
      
      // Подсветка (вспышка) в самом низу кадра (как на картинке)
      float bottomGlow = smoothstep(-3.8, -4.0, vPosition.y) * 2.0;
      
      // Мерцание
      float flash = 0.7 + 0.3 * sin(uTime * 2.0 + vRandomness * 10.0);
      
      gl_FragColor = vec4(color * (flash + bottomGlow), strength * (vType > 0.5 ? 0.3 : 0.85));
    }
  `
);

extend({ GoldParticleMaterial });

// --- КОМПОНЕНТ 5 СКРУЧЕННЫХ ЛИНИЙ ---
const GoldenStrandLines: React.FC = () => {
    const COUNT = 5;
    const POINTS = 60;

    const { lineData, tmpPos } = useMemo(() => {
        const tmpPos = new Float32Array(POINTS * 3);
        const lineData = Array.from({ length: COUNT }, (_, idx) => {
            const phase = (idx / COUNT) * Math.PI * 2;
            const geom = new LineGeometry();
            geom.setPositions(new Float32Array(POINTS * 3));
            const mat = new LineMaterial({
                linewidth: 4,
                color: new THREE.Color(1.0, 0.80, 0.38),
                transparent: true,
                opacity: 0.95,
                depthWrite: false,
                blending: THREE.AdditiveBlending,
                resolution: new THREE.Vector2(window.innerWidth, window.innerHeight),
            });
            return { line: new Line2(geom, mat), phase };
        });
        return { lineData, tmpPos };
    }, []);

    useFrame((state) => {
        const time = state.clock.getElapsedTime();
        lineData.forEach(({ line, phase }) => {
            for (let i = 0; i < POINTS; i++) {
                const y = ((i / (POINTS - 1)) * 8.0) - 4.0;
                const wave = getBaseWave(y, time);
                const twistAngle = y * 0.8 + time * 0.5 + phase;
                const radius = 0.08 + Math.abs(y) * 0.04;
                tmpPos[i * 3]     = wave.x + Math.sin(twistAngle) * radius;
                tmpPos[i * 3 + 1] = y;
                tmpPos[i * 3 + 2] = wave.z + Math.cos(twistAngle) * radius;
            }
            (line.geometry as LineGeometry).setPositions(tmpPos);
        });
    });

    return (
        <>
            {lineData.map(({ line }, idx) => (
                <primitive key={idx} object={line} />
            ))}
        </>
    );
};

// --- КОМПОНЕНТ СИСТЕМЫ ЧАСТИЦ ---
const ParticleSystem: React.FC = () => {
    const materialRef = useRef<GoldParticleMaterialType>(null);
    const totalParticles = 7000;

    const [positions, rand, spd, type] = useMemo(() => {
        const pos = new Float32Array(totalParticles * 3);
        const rand = new Float32Array(totalParticles);
        const spd = new Float32Array(totalParticles);
        const type = new Float32Array(totalParticles);

        for (let i = 0; i < totalParticles; i++) {
            pos[i * 3] = 0;
            pos[i * 3 + 1] = (Math.random() - 0.5) * 8.0;
            pos[i * 3 + 2] = 0;

            rand[i] = Math.random();
            spd[i] = 0.4 + Math.random() * 0.6;

            // 92% — мелкая пыль в потоке, 8% — крупные фоновые боке
            type[i] = Math.random() > 0.92 ? 1.0 : 0.0;
        }
        return [pos, rand, spd, type];
    }, []);

    useFrame((state) => {
        if (materialRef.current) {
            materialRef.current.uTime = state.clock.getElapsedTime();
        }
    });

    return (
        <points>
            <bufferGeometry>
                <bufferAttribute attach="attributes-position" args={[positions, 3]} />
                <bufferAttribute attach="attributes-aRandomness" args={[rand, 1]} />
                <bufferAttribute attach="attributes-aSpeed" args={[spd, 1]} />
                <bufferAttribute attach="attributes-aType" args={[type, 1]} />
            </bufferGeometry>
            <goldParticleMaterial
                ref={materialRef}
                transparent
                depthWrite={false}
                blending={THREE.AdditiveBlending}
            />
        </points>
    );
};

// --- ГЛАВНЫЙ ЭКРАН ---
export default function GoldParticleWave() {
    return (
        <div style={{ width: '100vw', height: '100vh', background: '#020204' }}>
            <Canvas
                camera={{ position: [0, 0, 3.8], fov: 65 }}
                gl={{ antialias: true, powerPreference: "high-performance" }}
            >
                <ParticleSystem />
                <GoldenStrandLines />
                <OrbitControls
                    enableZoom={true}
                    maxDistance={5}
                    minDistance={2}
                    enablePan={false}
                />
            </Canvas>
        </div>
    );
}