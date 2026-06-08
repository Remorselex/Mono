import {InteractiveSmoke} from './ThreeJs/GoldSmoke';
import {Canvas} from "@react-three/fiber";
import {PROJ_CONSTANTS} from "./Config.ts";
// import {useState} from "react";
// import GoldParticleWave from "./GoldSmokeAi.tsx";


const MyGoldSmokeController = () => {
    // const [turbulent, setTurbulent] = useState(false);

    return (
        <div style={{ width: '100vw', height: '100vh', position: 'relative', background: '#0a0a0a' }}>

            {/* Обычный HTML интерфейс поверх 3D Canvas */}
            <div style={{ position: 'absolute', top: 20, left: 20, zIndex: 10 }}>
                {/*<button*/}
                {/*    onClick={() => setTurbulent(!turbulent)}*/}
                {/*    style={{ padding: '10px 20px', cursor: 'pointer', background: '#dfb76c', border: 'none', borderRadius: '4px' }}*/}
                {/*>*/}
                {/*    {turbulent ? 'Успокоить дым' : 'Взболтать дым (Турбулентность)'}*/}
                {/*</button>*/}
            </div>

            {/* 3D Сцена */}
            <Canvas camera={{ position: [0, 0, 6] }}>
                <InteractiveSmoke count={PROJ_CONSTANTS.particles_density * PROJ_CONSTANTS.linesCount} isTurbulent={undefined} />
            </Canvas>
        </div>
    );

}


export default function App() {
    //return <GoldParticleWave/>

    return <MyGoldSmokeController/>
}
