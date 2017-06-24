'use strict';

let describe = require("mocha").describe;
let it = require("mocha").it;
let should = require('should');
let eon = require("..");

describe('Number', () => {
    it('should read/write roundtrip small integers', () => {
        should(eon.writeNumber(eon.readNumber('123')))
            .equal('123');
    });

    it.skip('should read/write roundtrip large integers (2^128)', () => {
        should(eon.writeNumber(eon.readNumber('340282366920938463463374607431768211456')))
            .equal('340282366920938463463374607431768211456');
    });

    it('should read/write roundtrip small decimals', () => {
        should(eon.writeNumber(eon.readNumber('0.123')))
            .equal('0.123');
    });

    it.skip('should read/write roundtrip large decimals', () => {
        should(eon.writeNumber(eon.readNumber('0.123456789123456789123456789')))
            .equal('0.123456789123456789123456789');
    });

    it('should read/write roundtrip small repeating decimals', () => {
        should(eon.writeNumber(eon.readNumber('0.(123)')))
            .equal('0.(123)');
    });

    it.skip('should read/write roundtrip large repeating decimals (1/97)', () => {
        should(eon.writeNumber(eon.readNumber('0.(010309278350515463917525773195876288659793814432989690721649484536082474226804123711340206185567)')))
            .equal('0.(010309278350515463917525773195876288659793814432989690721649484536082474226804123711340206185567)');
    });

    it('should keep decimal precision on add', () => {
        let n = eon.add(eon.readNumber('0.1'), eon.readNumber('0.2'));
        should(eon.writeNumber(n))
            .equal('0.3');
    });

    it('should compare equal a repeating decimal and a fraction', () => {
        let x = eon.readNumber('0.(032258064516129)');
        let y = eon.divide(eon.readNumber('1'), eon.readNumber('31'));
        should(eon.isEqualNumber(x, y)).ok();
    });

    it('should compare equal a decimal and a fraction', () => {
        let x = eon.readNumber('0.5');
        let y = eon.divide(eon.readNumber('1'), eon.readNumber('2'));
        should(eon.isEqualNumber(x, y)).ok();
    });
});
