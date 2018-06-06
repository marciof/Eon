'use strict';

let mathjs = require('mathjs');
mathjs.config({number: 'Fraction'});

module.exports = {
    readNumber(text) {
        return mathjs.fraction(text);
    },

    writeNumber(number) {
        return mathjs.format(number, {fraction: 'decimal', notation: 'fixed'});
    },

    isNumberEqual(x, y, ...rest) {
        for (let n of [y, ...rest]) {
            if (!mathjs.equal(x, n)) {
                return false;
            }
        }
        return true;
    },

    divide(x, y, ...rest) {
        return [x, y, ...rest].reduce(
            (result, value) => mathjs.divide(result, value));
    },

    multiply(x, y, ...rest) {
        return mathjs.multiply(x, y, ...rest);
    },

    add(x, y, ...rest) {
        return mathjs.add(x, y, ...rest);
    },

    subtract(x, y, ...rest) {
        return [x, y, ...rest].reduce(
            (result, value) => mathjs.subtract(result, value));
    },
};
