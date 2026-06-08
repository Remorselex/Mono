import { useRef, useMemo } from 'react';
import { useFrame } from '@react-three/fiber';
import * as THREE from 'three';
import {createCircleTexture} from "./Shaders/GoldParticle.tsx";
//import {traa} from "three/examples/jsm/tsl/display/TRAANode";
// import {PROJ_CONSTANTS} from "../Config.ts";

const PARTICLE_CONFIG = {
  size: 0.04,
  color: "#dfb76c",
  transparent: true,
  opacity: 1,
  depthWrite: false
}

interface InteractiveSmokeProps {
  count?: number;
  isTurbulent?: boolean;
}

// Компонент самих частиц
export function InteractiveSmoke({ count = 6000, isTurbulent = false }: InteractiveSmokeProps) {
  const pointsRef = useRef<THREE.Points>(null);

  // Создаем массив точек один раз
  // 1. При инициализации возвращаем разброс по Y
  const positions = useMemo(() => {
    const line = new Float32Array(count * 3); // строго count * 3
    for (let i = 0; i < count; i++) {
      line[i * 3]     = (Math.random() - 0.5) * 18; // X (длина шлейфа)
      line[i * 3 + 1] = (Math.random() - 0.5) * 2;  // Y (базовая высота дыма)
      //line[i * 3 + 2] = (Math.random() - 0.5) * 2;  // Z (глубина для объема)
    }
    return line;
  }, [count]);

// 2. Внутри useFrame меняем логику обновления
  useFrame((state) => {
    if (!pointsRef.current) return;

    const { clock, pointer } = state;
    const time = clock.getElapsedTime();
    const attr = pointsRef.current.geometry.attributes.position as THREE.BufferAttribute;
    const geoPositions = attr.array as Float32Array;

      for (let i = 0; i < count; i++) {
        const i3 = i * 3;
        const x = geoPositions[i3];


        let mouseDestination= 0;
        // LAYER 1: Макро-волна (Большой ветер)
        const macroAmplitude = 0.5;   // Высота большой волны
        const macroFrequency = 0.5;   // Плотность большой волны (чем меньше, тем она длиннее)
        const macroSpeed = 2;       // Скорость бега большой волны

        const wave = Math.sin(x * macroFrequency + time * macroSpeed) * macroAmplitude;

        // LAYER 2: Микро-волна (Хаос и рябь)
        const microAmplitude = 0.4;  // Высота мелкой ряби
        const microFrequency = .5;   // Плотность мелкой ряби
        const microSpeed = 1.0;       // Скорость вибрации ряби
        const lineOffset = (i % 5) * 0.5; // Сдвиг фазы для каждой точки

        // const distanceToMouse = Math.abs(x - pointer.x * 5);
        // if (distanceToMouse < 2 * 9999999) {
        //   mouseDestination = pointer.y * (2 - distanceToMouse) * 0.09;
        // }
        const noise = Math.sin(x * microFrequency + time * microSpeed + lineOffset ) * microAmplitude;

        // --- ИТОГОВЫЙ СЛОЕНЫЙ ПИРОГ ---
        geoPositions[i3 + 1] = (wave + mouseDestination) + noise;
        //geoPositions[i3 + 2] = wave + noise

      }


    attr.needsUpdate = true;
  });

  const particleTexture = useMemo(() => createCircleTexture(), []);

  return (
    <points ref={pointsRef}>
      <bufferGeometry>
        {/* args передает [array, itemSize] в конструктор BufferAttribute (R3F v9 API) */}
        <bufferAttribute
          attach="attributes-position"
          args={[positions, 3]}
        />
      </bufferGeometry>
      <pointsMaterial
        map={particleTexture}
        blending={THREE.AdditiveBlending}
        {...PARTICLE_CONFIG}
      />
    </points>
  );
}
