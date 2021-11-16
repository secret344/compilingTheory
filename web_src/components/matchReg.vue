<script>
import { ref, reactive } from "vue";
export default {
  name: "match_reg",
  props: {},
  data() {
    return {
      greeting: "match_reg",
    };
  },
  setup(props, context) {
    const content = reactive({
      name: "所要匹配的字符串(打开devtools查看结果)",
    });

    const onchange = (e) => {
      content.reg = e.target.value;
      context.emit("reg-match", e.target.value);
    };
    const oninput = (e) => {};

    return {
      content,
      onchange,
      oninput,
    };
  },
};
</script>

<template>
  <div>
    <p>{{ content.name }}</p>
    <textarea
      placeholder="请输入需要匹配的字符串:"
      cols="30"
      rows="10"
      v-model="content.reg"
      @change="onchange"
      @input="oninput"
    ></textarea>
  </div>
</template>

<style>
.greeting {
  color: red;
  font-weight: bold;
}

</style>