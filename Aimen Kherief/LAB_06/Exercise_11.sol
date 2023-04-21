//SPDX-License-Identifier: GLP-3.0
pragma solidity >=0.5.0 <0.8.0;

contract Factory { 
    uint idDigits=16;
    uint idModulus=10^idDigits;

    struct Product {
        string name;
        uint id;
    }
    Product[] public products;

    event NewProduct (uint ArrayProductId,  string name, uint id);

    function _createProduct(string memory _name, uint _id) private {
        products.push(Product(_name,_id));
        uint productId= (products.length - 1);
        emit NewProduct(productId,_name,_id); 
    }
    function _generateRandomId(string memory _str) private view returns(uint) {
        uint rand=uint(keccak256(abi.encodePacked(_str)));
        return (rand%idModulus);
    } 
    function createRandomProduct(string memory _name) public {
        uint randId=_generateRandomId(_name);
        _createProduct(_name, randId);
    } 

    mapping (uint => address) public productToOwner;
    mapping (address => uint) ownerProductCount;

    function _Ownership (uint _productId) private { 
        productToOwner[_productId] = msg.sender;
        ownerProductCount[msg.sender]++;
    }

}

