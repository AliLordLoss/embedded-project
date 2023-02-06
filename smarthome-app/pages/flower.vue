<template>
  <div>
    <v-row>
      <v-spacer />
      <v-col cols="10" lg="6">
        <h2 class="data">
          Your home Gas Value is:
          {{ gas !== null ? gas + " ppm" : "unknown" }}
        </h2>
      </v-col>
      <v-spacer />
    </v-row>

    <v-row>
      <v-spacer />
      <v-col cols="10" lg="6">
        <h2 class="data">
          Your vases Moisture is:
          {{ moisture !== null ? moisture + "%" : "unknown" }}
        </h2>
      </v-col>
      <v-spacer />
    </v-row>
  </div>
</template>

<script>
export default {
  data() {
    return {
      gas: null,
      moisture: null,
    };
  },
  created() {
    this.$axios
      .get(`http://${this.$store.state.ip3}`, { timeout: 1000 })
      .then((res) => {
        this.gas = res.data.gas;
        this.moisture = res.data.moisture;
      })
      .catch(() => {
        this.$store.dispatch(
          "setSnackbarMessage",
          "Something went wrong trying to get data from Smart Home Gas & Moisture Module!"
        );
        this.$store.dispatch("setSnackbar", true);
      });
  },
};
</script>

<style>
.data {
  text-align: center;
}
</style>
