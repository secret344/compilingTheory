<script>
import { ref, reactive, nextTick, computed, watchEffect } from "vue";
import * as d3 from "d3-graphviz";
export default {
  name: "graphviz",
  props: {
    name: String,
    graphIntermediate: Object,
  },
  data() {
    return {};
  },

  setup(props, context) {
    const content = reactive({
      name: props.name || "graph",
      reg: props.graphIntermediate,
      d3_Instance: null,
    });

    const DOTdata = computed(() => {
      return props.graphIntermediate;
    });

    const d3_Render = (text) => {
      nextTick(() => {
        const d3_Instance = content.d3_Instance;
        d3_Instance && d3_Instance.destroy();
        content.d3_Instance = d3
          .graphviz(`#${content.name}`)
          .zoom(false)
          .renderDot(text || "digraph graphname  {a->b}");
      });
    };

    watchEffect(() => {
      let arr = DOTdata.value;
      let text = "";
      let color =
        'digraph {rankdir="LR"  size="10,10" regular=true node [style="filled"];';
      for (let i = 0; i < arr.length; i++) {
        const { id, value, next1, next2 } = arr[i];
        if (next1) text += ` ${id} -> ${next1} [label="${value}"] ; `;
        if (next2) text += ` ${id} -> ${next2} [label="${value}"] ; `;
      }
      text += "}";
      text = color += text;
      d3_Render(text);
    }, [DOTdata]);

    return {
      content,
      DOTdata,
    };
  },
};
</script>

<template>
  <div class="graphviz_box">
    <h2>{{ content.name }}</h2>
    <div :id="content.name"></div>
  </div>
</template>

<style>
.graphviz_box {
  border: 1px solid rosybrown;
}
#graph {
  min-height: 500px;
}
</style>