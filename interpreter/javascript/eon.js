'use strict';

let mathjs = require('mathjs');
mathjs.config({number: 'Fraction'});

module.exports = {
    readNumber: function (text) {
        return mathjs.fraction(text);
    },

    writeNumber: function (number) {
        return mathjs.format(number, {fraction: 'decimal', notation: 'fixed'})
    },

    isEqualNumber: function (x, y, ...rest) {
        for (let n of [y, ...rest]) {
            if (!mathjs.equal(x, n)) {
                return false;
            }
        }
        return true;
    },

    divide: function (x, y, ...rest) {
        return [x, y, ...rest].reduce((acc, value) => {
            return mathjs.divide(acc, value);
        });
    },

    multiply: function (x, y, ...rest) {
        return mathjs.multiply(x, y, ...rest);
    },

    add: function (x, y, ...rest) {
        return mathjs.add(x, y, ...rest);
    },

    subtract: function (x, y, ...rest) {
        return [x, y, ...rest].reduce((acc, value) => {
            return mathjs.subtract(acc, value);
        });
    },
};
