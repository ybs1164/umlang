module.exports = function parser(tokens) {
  this.currentIndex = 0;
  this.getToken = () => {
    if (this.currentIndex > tokens.length) return undefined;
    return tokens[this.currentIndex++];
  };

  this.parseTree = {
    type: "Program",
    body: [],
  };

  this.token = this.getToken();

  while (this.token) {
    // todo
  }
}
