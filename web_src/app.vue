<script>
export default {
  name: "App",
  data() {
    return {
      greeting: "Hello World!",
    };
  },
};
</script>

<template>
  <p class="greeting">{{ greeting }}</p>
</template>

<style>
.greeting {
  color: red;
  font-weight: bold;
}
</style>