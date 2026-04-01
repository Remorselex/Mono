console.log('🔬 Testing Node.js C++ Addon (CMake build)\n');

try {
    // @ts-ignore
    const native = await import('../build/Release/native.node');
    console.log('✅ C++ Addon loaded successfully!');
    console.log('   2 + 3 =', native.add(2, 3));
    console.log('   10 + 25 =', native.add(10, 25));
} catch (err) {
    console.log('⚠️  C++ Addon not built yet.');
    console.log('   Run: pnpm build');
    console.log('   Error:', err);
}
