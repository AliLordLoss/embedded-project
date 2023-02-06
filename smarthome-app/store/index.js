export const state = () => ({
  ip1: localStorage.getItem("ip1")
    ? localStorage.getItem("ip1")
    : "192.168.43.109", // temperature

  ip2: localStorage.getItem("ip2")
    ? localStorage.getItem("ip2")
    : "192.168.43.46", // light

  ip3: localStorage.getItem("ip3")
    ? localStorage.getItem("ip3")
    : "192.168.43.168", // gas & soil moisture

  snackbar: false,
  snackbarMessage: "",
});

export const getters = {
  // getIp1(state) {
  //   return state.ip1;
  // },
  // getIp2(state) {
  //   return state.ip2;
  // },
  // getIp3(state) {
  //   return state.ip3;
  // },
};

export const mutations = {
  SET_IP1(state, data) {
    state.ip1 = data;
    localStorage.setItem("ip1", data);
  },
  SET_IP2(state, data) {
    state.ip2 = data;
    localStorage.setItem("ip2", data);
  },
  SET_IP3(state, data) {
    state.ip3 = data;
    localStorage.setItem("ip3", data);
  },
  SET_SNACKBAR(state, data) {
    state.snackbar = data;
  },
  SET_SNACKBAR_MESSAGE(state, data) {
    state.snackbarMessage = data;
  },
};

export const actions = {
  setIp1({ commit }, data) {
    commit("SET_IP1", data);
  },
  setIp2({ commit }, data) {
    commit("SET_IP2", data);
  },
  setIp3({ commit }, data) {
    commit("SET_IP3", data);
  },
  setSnackbar({ commit }, data) {
    commit("SET_SNACKBAR", data);
  },
  setSnackbarMessage({ commit }, data) {
    commit("SET_SNACKBAR_MESSAGE", data);
  },
};
