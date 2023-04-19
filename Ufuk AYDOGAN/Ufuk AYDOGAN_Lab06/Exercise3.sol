//SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.10;

contract Exercise3 {
uint public myidDigits = 5228140614098209; 
uint z = myidDigits ** 2; 
    uint public idModulus = uint(z);
}
//as power 10 is big, I proceeded with 2 to show code is working