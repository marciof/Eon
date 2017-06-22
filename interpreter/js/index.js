'use strict';

let nerdamer = require('nerdamer');
let immutable = require('immutable');

function _chainOperator(operator, operands) {
    let substitutions = {};
    let variables = [];

    operands.forEach((operand, index) => {
        let name = 'var_' + index;
        substitutions[name] = operand;
        variables.push(name);
    });

    return nerdamer(variables.join(operator), substitutions);
}

function Number(x) {
    return nerdamer(x);
}

function divide(x, y, ...rest) {
    return _chainOperator('/', [x, y, ...rest]);
}

function multiply(x, y, ...rest) {
    return _chainOperator('*', [x, y, ...rest]);
}

function add(x, y, ...rest) {
    return _chainOperator('+', [x, y, ...rest]);
}

function subtract(x, y, ...rest) {
    return _chainOperator('-', [x, y, ...rest]);
}

function Map(...keyValuePairs) {
    return immutable.OrderedMap().merge(...keyValuePairs);
}

function put(map, key, value) {
    return map.set(key, value);
}

console.log(
    multiply(
        add(
            Number(4),
            divide(Number(1), Number(3))),
        Number(3))
    .evaluate()
    .text());

let Person = Map({'name': ''}, {'age': 0});
let bob = put(put(Person, 'name', 'Bob'), 'age', 20);

console.log(Person);
console.log(bob);
