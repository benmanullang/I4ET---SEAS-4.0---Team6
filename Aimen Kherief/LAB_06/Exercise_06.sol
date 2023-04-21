//SPDX-License-Identifier: GLP-3.0
pragma solidity >=0.5.0 <0.8.0;

contract Factory {
    uint public idDigits = 16;
    uint public idModulus = 10 ** idDigits;

    struct Product {
        string name;
        uint id;
    }

    Product[] public products;

    function createProduct(string memory _name, uint _id) private {
        Product memory newProduct = Product(_name, _id);
        products.push(newProduct);
    }
}

