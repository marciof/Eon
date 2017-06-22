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

function number(x) {
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

console.log(
    multiply(
        add(
            number(4),
            divide(number(1), number(3))),
        number(3))
    .evaluate()
    .text());

let Person = immutable.OrderedMap().set('name', '').set('age', 0);
let bob = Person.set('name', 'Bob').set('age', 20);

console.log(Person);
console.log(bob);
