
<script>
import InputReg from "./components/inputReg";
import MatchReg from "./components/matchReg";
import { WebAssemblyFun, regstr } from "./server/c_bind";
import { ref, reactive, onBeforeMount } from "vue";

export default {
  name: "App",
  components: {
    InputReg,
    MatchReg,
  },
  setup() {
    const regValue = reactive({
      value: regstr,
      defValue: regstr,
      matchValue: "",
    });
    let wsFun = null;
    console.log(regstr);
    onBeforeMount(async () => {
      wsFun = await WebAssemblyFun();
    });

    const onregcontent = (value) => {
      regValue.value = value;
    };

    const onregmatch = (value) => {
      regValue.matchValue = value;
    };

    const onclick = () => {
      const { regParse, matchStr } = wsFun;
      let str = regParse(regValue.value);
      console.log("格式化结果", JSON.parse(str));
    };
    const onclickmatch = () => {
      const { matchStr } = wsFun;
      matchStr(regValue.matchValue);
    };
    return { onregcontent, onregmatch, onclickmatch, onclick, regValue };
  },
};
</script>

<template>
  <div>
    <div class="textarea_box">
      <InputReg
        @reg-content="onregcontent"
        :defValue="regValue.defValue"
      ></InputReg>
      <MatchReg @reg-match="onregmatch"></MatchReg>
    </div>
    <button @click="onclick">获取数据</button
    ><button @click="onclickmatch">开始匹配</button>
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
.textarea_box {
  display: flex;
}
textarea {
  min-width: 400px;
  margin-left: 10px;
}
</style>