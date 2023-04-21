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
        uint productId = products.push(newProduct) - 1;
        emit NewProduct(productId, _name, _id);
    }

    function _generateRandomId(string memory _str) private view returns (uint) {
        uint rand = uint(keccak256(abi.encodePacked(_str)));
        return rand % idModulus;
    }

    function createRandomProduct(string memory _name) public {
        uint randId = _generateRandomId(_name);
        createProduct(_name, randId);
    }

    event NewProduct(uint indexed ArrayProductId, string name, uint id);
}


