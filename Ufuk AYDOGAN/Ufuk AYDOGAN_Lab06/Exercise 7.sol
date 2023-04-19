//SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.10;

contract Exercise {
 uint public myidDigits = 5228140614098209; 
uint z = myidDigits ** 2; 
    uint public idModulus = uint(z);

    struct Product {
        string name;
        uint id;
    }

    Product[] public product1;

   function _createProduct(string memory _name, uint _id) private {
    Product memory new_Product = Product(_name, _id);
    product1.push(new_Product);
    }

    function _generateRandomId(string memory _str) private view returns (uint) {

    }
}