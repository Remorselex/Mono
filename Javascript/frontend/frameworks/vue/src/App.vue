<script setup lang="ts">
import { ref } from 'vue'

const count = ref(0)
</script>

<template>
  <div>
    <h1>Vite + Vue + TypeScript</h1>
    <button @click="count++">count is {{ count }}</button>
  </div>
</template>
