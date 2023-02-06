<template>
  <div>
    <v-row>
      <v-spacer />
      <v-col cols="10" lg="6">
        <h2 class="data">
          Your home temperature is:
          {{ temperature ? temperature + "°C" : "unknown" }}
        </h2>
      </v-col>
      <v-spacer />
    </v-row>

    <v-row>
      <v-col>
        <div class="data">
          <h2>Cooler:</h2>
          <v-switch :value="cooler === 1" @click.prevent="switchCooler" />
        </div>
      </v-col>
    </v-row>

    <v-row>
      <v-col>
        <div class="data">
          <h2>Heater:</h2>
          <v-switch :value="heater === 1" @click.prevent="switchHeater" />
        </div>
      </v-col>
    </v-row>
  </div>
</template>

<script>
export default {
  data() {
    return {
      temperature: null,
      cooler: null,
      heater: null,
    };
  },
  methods: {
    switchCooler() {
      if (this.cooler === 0) {
        this.$axios
          .get(`http://${this.$store.state.ip1}/cooler-on`, { timeout: 1000 })
          .then(() => {
            this.cooler = 1;
          })
          .catch(() => {
            this.$store.dispatch(
              "setSnackbarMessage",
              "Something went wrong trying to turn on the Cooler!"
            );
            this.$store.dispatch("setSnackbar", true);
          });
      } else {
        this.$axios
          .get(`http://${this.$store.state.ip1}/cooler-off`, { timeout: 1000 })
          .then(() => {
            this.cooler = 0;
          })
          .catch(() => {
            this.$store.dispatch(
              "setSnackbarMessage",
              "Something went wrong trying to turn off the Cooler!"
            );
            this.$store.dispatch("setSnackbar", true);
          });
      }
    },
    switchHeater() {
      if (this.heater === 0) {
        this.$axios
          .get(`http://${this.$store.state.ip1}/heater-on`, { timeout: 1000 })
          .then(() => {
            this.heater = 1;
          })
          .catch(() => {
            this.$store.dispatch(
              "setSnackbarMessage",
              "Something went wrong trying to turn on the Heater!"
            );
            this.$store.dispatch("setSnackbar", true);
          });
      } else {
        this.$axios
          .get(`http://${this.$store.state.ip1}/heater-off`, { timeout: 1000 })
          .then(() => {
            this.heater = 0;
          })
          .catch(() => {
            this.$store.dispatch(
              "setSnackbarMessage",
              "Something went wrong trying to turn off the Heater!"
            );
            this.$store.dispatch("setSnackbar", true);
          });
      }
    },
  },
  created() {
    this.$axios
      .get(`http://${this.$store.state.ip1}`, { timeout: 1000 })
      .then((res) => {
        this.temperature = res.data.temperature;
        this.cooler = res.data.cooler;
        this.heater = res.data.heater;
      })
      .catch(() => {
        this.$store.dispatch(
          "setSnackbarMessage",
          "Something went wrong trying to get data from Smart Home Temperature Module!"
        );
        this.$store.dispatch("setSnackbar", true);
      });
  },
};
</script>

<style>
.data {
  text-align: center;
  width: 100%;
  display: flex;
  flex-direction: row;
  align-items: center;
  justify-content: center;
  gap: 16px;
}
</style>
