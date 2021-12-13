
<script>
import InputReg from "./components/inputReg";
import MatchReg from "./components/matchReg";
import Graphviz from "./components/graphviz";
import { formatterNFAIntermediate } from "./utils";
import { WebAssemblyFun, regstr } from "./server/c_bind";
import { ref, reactive, onBeforeMount } from "vue";

export default {
  name: "App",
  components: {
    InputReg,
    MatchReg,
    Graphviz,
  },
  setup() {
    const regValue = reactive({
      value: regstr,
      defValue: regstr,
      matchValue: "",
      dotArr: [],
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
      const { regParse, matchStr, dfaParse } = wsFun;
      let str = regParse(regValue.value);
      regValue.dotArr = formatterNFAIntermediate(JSON.parse(str));
      console.log("格式化结果(NFA)", regValue.dotArr, JSON.parse(str));
      // dfaParse();
    };
    const onclickmatch = () => {
      const { matchStr, dfaParse } = wsFun;
      matchStr(regValue.matchValue);
    };
    return { onregcontent, onregmatch, onclickmatch, onclick, regValue };
  },
};
</script>

<template>
  <div class="app_box">
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
        punctuation:[,;]<br />
        string:(["](.)*["])|(['](.)*['])<br />
      </p>
    </div>
    <div>
      <h2>NFA</h2>
      <div class="graphviz_flex">
        <div v-for="item in regValue.dotArr" :key="item.id">
          <Graphviz :name="item.id" :graphIntermediate="item.value"></Graphviz>
        </div>
      </div>
    </div>
  </div>
</template>

<style>
.app_box {
  display: flex;
  flex: 1 1;
}
.greeting {
  color: red;
  font-weight: bold;
}
.textarea_box {
  display: flex;
}
.graphviz_flex {
  display: flex;
  flex-wrap: wrap;
}
textarea {
  min-width: 400px;
  margin-left: 10px;
}
</style>