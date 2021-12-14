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

    const reset_room = () => {
      try {
        content.d3_Instance.resetZoom();
      } catch (error) {}
    };

    const d3_Render = (text) => {
      nextTick(() => {
        const d3_Instance = content.d3_Instance;
        d3_Instance && d3_Instance.destroy();
        content.d3_Instance = d3
          .graphviz(`#${content.name}`, {
            useWorker: false,
            width: 1000,
          })
          .zoom(true)
          .renderDot(text || "digraph graphname  {a->b}");
        setTimeout(reset_room);
      });
    };

    watchEffect(() => {
      let arr = DOTdata.value;
      let text = "";
      let color =
        'digraph {rankdir="LR"  size="10,10" regular=true node [style="filled"];';
      for (let i = 0; i < arr.length; i++) {
        const { id, value, next1, next2, tooltip } = arr[i];
        // labeltooltip
        tooltip && (text = `${id} [tooltip="${tooltip}" ];` + text);
        if (next1) text += `${id} -> ${next1} [label="${value}"] ; `;
        if (next2) text += `${id} -> ${next2} [label="${value}"] ; `;
      }
      text += "}";
      text = color += text;
      d3_Render(text);
    }, [DOTdata]);

    return {
      content,
      DOTdata,
      reset_room,
    };
  },
};
</script>

<template>
  <div class="graphviz_box">
    <h2>{{ content.name }}</h2>
    <button @click="reset_room">reset zoom</button>
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