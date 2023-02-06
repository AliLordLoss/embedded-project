<template>
  <v-row justify="center" align="center">
    <v-col cols="10" lg="6">
      <v-text-field
        label="temperature controller ip"
        :value="ip1"
        @change="setIp1"
      />

      <v-text-field label="light controller ip" :value="ip2" @change="setIp2" />

      <v-text-field
        label="gas & soil moisture ip"
        :value="ip3"
        @change="setIp3"
      />
    </v-col>
  </v-row>
</template>

<script>
import { mapActions } from "vuex";

export default {
  computed: {
    ip1() {
      return this.$store.state.ip1;
    },
    ip2() {
      return this.$store.state.ip2;
    },
    ip3() {
      return this.$store.state.ip3;
    },
  },
  methods: {
    ...mapActions({
      setIp1: "setIp1",
      setIp2: "setIp2",
      setIp3: "setIp3",
    }),
  },
};
</script>
