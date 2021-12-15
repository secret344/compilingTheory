
<script>
import InputReg from "./components/inputReg";
import MatchReg from "./components/matchReg";
import Graphviz from "./components/graphviz";
import { formatterNFAIntermediate, formatterSTTIntermediate } from "./utils";
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
      dfaSTT: [],
      dfaJson: null,
    });
    let wsFun = null;
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
      const { regParse, getDfaJson } = wsFun;
      let str = regParse(regValue.value);
      regValue.dotArr = formatterNFAIntermediate(JSON.parse(str));
      regValue.dfaJson = JSON.parse(getDfaJson());
      regValue.dfaSTT = [];
    };

    const lookDfaJson = () => {
      regValue.dfaSTT = [];
      let dfaJson = regValue.dfaJson;
      for (const key in dfaJson) {
        regValue.dfaSTT.push({
          name: key,
          dfa: formatterSTTIntermediate(dfaJson[key].dfaSTT, dfaJson[key]),
          miniDfa: formatterSTTIntermediate(
            dfaJson[key].minimizeDfa.minDfa,
            dfaJson[key],
            true
          ),
        });
      }
    };

    const onclickmatch = () => {
      const { matchStr } = wsFun;
      matchStr(regValue.matchValue);
    };
    return {
      onregcontent,
      onregmatch,
      onclickmatch,
      onclick,
      regValue,
      lookDfaJson,
    };
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

    <div>
      <h2>DFA AND MINIDFA(悬浮节点可见详细提示)</h2>
      <button @click="lookDfaJson">
        查看dfa状态转移图(<strong style="color: red"
          >请使用简易的正则表达式查看,不要携带控制字符</strong
        >)
      </button>
      <div class="graphviz_flex graphviz_dfa">
        <div v-for="item in regValue.dfaSTT" :key="item.name">
          <Graphviz
            :name="item.name + '_dfa'"
            :graphIntermediate="item.dfa"
          ></Graphviz>
          <Graphviz
            :name="item.name + '_miniDfa'"
            :graphIntermediate="item.miniDfa"
          ></Graphviz>
        </div>
      </div>
    </div>
  </div>
</template>

<style>
.app_box {
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
.graphviz_dfa {
  flex-direction: column;
}
textarea {
  min-width: 400px;
  margin-left: 10px;
}
</style>