
<script>
import InputReg from "./components/inputReg";
import { WebAssemblyFun } from "./server/c_bind";
import { ref, reactive, onBeforeMount } from "vue";

export default {
  name: "App",
  components: {
    InputReg,
  },
  setup() {
    const regValue = reactive({ value: "" });
    let wsFun = null;

    onBeforeMount(async () => {
      wsFun = await WebAssemblyFun();
    });

    const onregcontent = (value) => {
      regValue.value = value;
    };

    const onclick = () => {
      console.log(wsFun);
      const { regParse, matchStr } = wsFun;
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
    <div>正则example:</div>
    <p>
      id:[a-zA-Z]([a-zA-Z0-9_])*<br />
      float:[0-9]+\.[0-9]*<br />
      int:[0-9]+<br />
      optr:((&lt;|!|\+|=|\||\-|\*|&)+)|((&lt;|!|\+|=|\||\-|\*|&)=)|(\[|\]|\(|\))
      <br />
      punctuation:[,;]<br />
      string:(["](.)*["])|(['](.)*['])<br />
    </p>
  </div>
</template>

<style>
.greeting {
  color: red;
  font-weight: bold;
}
</style>