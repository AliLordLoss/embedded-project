<template>
  <v-app dark>
    <v-navigation-drawer v-model="drawer" fixed app>
      <v-list>
        <v-list-item
          v-for="(item, i) in items"
          :key="i"
          :to="item.to"
          router
          exact
        >
          <v-list-item-action>
            <v-icon>{{ item.icon }}</v-icon>
          </v-list-item-action>
          <v-list-item-content>
            <v-list-item-title v-text="item.title" />
          </v-list-item-content>
        </v-list-item>
      </v-list>
    </v-navigation-drawer>
    <v-app-bar fixed app>
      <v-app-bar-nav-icon @click.stop="drawer = !drawer" />
    </v-app-bar>
    <v-main>
      <v-container>
        <Nuxt />
      </v-container>
    </v-main>
    <v-footer app>
      <span>&copy; {{ new Date().getFullYear() }}</span>
    </v-footer>

    <v-snackbar :value="snackbar">
      {{ snackbarMessage }}

      <template v-slot:action="{ attrs }">
        <v-btn color="pink" text v-bind="attrs" @click="setSnackbar(false)">
          Close
        </v-btn>
      </template>
    </v-snackbar>
  </v-app>
</template>

<script>
import { mapActions } from "vuex";

export default {
  computed: {
    snackbar() {
      return this.$store.state.snackbar;
    },
    snackbarMessage() {
      return this.$store.state.snackbarMessage;
    },
  },
  methods: {
    ...mapActions({
      setSnackbar: "setSnackbar",
    }),
  },
  data() {
    return {
      drawer: false,
      items: [
        {
          icon: "mdi-apps",
          title: "Welcome",
          to: "/",
        },
        {
          icon: "mdi-thermometer",
          title: "Home Temperature",
          to: "/temperature",
        },
        {
          icon: "mdi-lightbulb",
          title: "Home Light",
          to: "/light",
        },
        {
          icon: "mdi-flower-tulip",
          title: "Gas & Vases condition",
          to: "/flower",
        },
      ],
    };
  },
};
</script>
