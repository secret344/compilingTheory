
<script>
import InputReg from "./components/inputReg";
import { WebAssemblyFun } from "./server/c_bind";
import { ref, reactive } from "vue";

export default {
  name: "App",
  components: {
    InputReg,
  },
  setup() {
    const regValue = reactive({ value: "" });

    const onregcontent = (value) => {
      regValue.value = value;
    };
    const onclick = async () => {
      const { regParse, matchStr } = await WebAssemblyFun();
      console.log(regParse);
      let str = regParse(regValue.value);
      console.log("格式化结果", JSON.parse(str));
    };
    return { onregcontent, onclick };
  },
};
</script>

<template>
  <div>
    <InputReg @reg-content="onregcontent" :defValue="123"></InputReg>
    <button @click="onclick">获取数据</button>
  </div>
</template>

<style>
.greeting {
  color: red;
  font-weight: bold;
}
</style>