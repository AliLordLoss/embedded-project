<template>
  <div>
    <v-row>
      <v-spacer />
      <v-col cols="10" lg="6">
        <h2 class="data">
          Your home light is:
          {{ light !== null ? light + " lux" : "unknown" }}
        </h2>
      </v-col>
      <v-spacer />
    </v-row>

    <v-row>
      <v-col>
        <div class="data">
          <h2>Lamp:</h2>
          <v-switch
            :value="lamp === 1"
            :disabled="lamp === null"
            @click.prevent="switchLamp"
          />
        </div>
      </v-col>
    </v-row>

    <v-row>
      <v-col cols="12">
        <div class="data">
          <h2>Curtain is: {{ curtain * 10 }}% opened</h2>
        </div>
      </v-col>
      <v-col cols="12">
        <div class="data">
          <v-btn
            class="mx-2"
            fab
            dark
            small
            color="primary"
            @click="closeCurtain"
            :disabled="curtain === null || curtain <= 0"
          >
            <v-icon dark> mdi-minus </v-icon>
          </v-btn>
          <v-btn
            class="mx-2"
            fab
            dark
            small
            color="primary"
            @click="openCurtain"
            :disabled="curtain === null || curtain >= 10"
          >
            <v-icon dark> mdi-plus </v-icon>
          </v-btn>
        </div>
      </v-col>
    </v-row>
  </div>
</template>

<script>
export default {
  data() {
    return {
      light: null,
      lamp: null,
      curtain: null,
    };
  },
  methods: {
    getData() {
      this.$axios
        .get(`http://${this.$store.state.ip2}`, { timeout: 1000 })
        .then((res) => {
          this.light = res.data.light;
          this.lamp = res.data.lamp;
          this.curtain = res.data.curtain;
        })
        .catch(() => {
          this.$store.dispatch(
            "setSnackbarMessage",
            "Something went wrong trying to get data from Smart Home Light Module!"
          );
          this.$store.dispatch("setSnackbar", true);
        });
    },
    openCurtain() {
      this.$axios
        .get(`http://${this.$store.state.ip2}/open-curtain`, { timeout: 1000 })
        .then(() => {
          this.curtain++;
          setTimeout(() => this.getData(), 10000);
        })
        .catch(() => {
          this.$store.dispatch(
            "setSnackbarMessage",
            "Something went wrong trying to open the curtains!"
          );
          this.$store.dispatch("setSnackbar", true);
        });
    },
    closeCurtain() {
      this.$axios
        .get(`http://${this.$store.state.ip2}/close-curtain`, { timeout: 1000 })
        .then(() => {
          this.curtain--;
          setTimeout(() => this.getData(), 7000);
        })
        .catch(() => {
          this.$store.dispatch(
            "setSnackbarMessage",
            "Something went wrong trying to close the curtains!"
          );
          this.$store.dispatch("setSnackbar", true);
        });
    },
    switchLamp() {
      if (this.lamp === 0) {
        this.$axios
          .get(`http://${this.$store.state.ip2}/lamp-on`, { timeout: 1000 })
          .then(() => {
            this.lamp = 1;
            setTimeout(() => this.getData(), 2000);
          })
          .catch(() => {
            this.$store.dispatch(
              "setSnackbarMessage",
              "Something went wrong trying to turn on the lamp!"
            );
            this.$store.dispatch("setSnackbar", true);
          });
      } else {
        this.$axios
          .get(`http://${this.$store.state.ip2}/lamp-off`, { timeout: 1000 })
          .then(() => {
            this.lamp = 0;
            setTimeout(() => this.getData(), 2000);
          })
          .catch(() => {
            this.$store.dispatch(
              "setSnackbarMessage",
              "Something went wrong trying to turn off the lamp!"
            );
            this.$store.dispatch("setSnackbar", true);
          });
      }
    },
  },
  created() {
    this.getData();
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
