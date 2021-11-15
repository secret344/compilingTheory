<script>
import { ref, reactive } from "vue";
export default {
  name: "input_reg",
  props: {
    defValue: String,
  },
  data() {
    return {
      greeting: "input_reg",
    };
  },
  setup(props, context) {
    const content = reactive({ name: "正则表达式(打开devtools查看结果)", reg: props.defValue });

    const onchange = (e) => {
      content.reg = e.target.value;
      context.emit("reg-content", e.target.value);
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
      placeholder="请输入需要格式化的正则表达式:"
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