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
    mapping (uint => address) public productToOwner;
    mapping (address => uint) public ownerProductCount;

    event New_Product(uint indexed ArrayProductId, string name, uint id);
    function createRandomProduct(string memory _name) public {
        uint randId = _generateRandomId(_name);
        _createProduct(_name, randId);
    }

   function _createProduct(string memory _name, uint _id) private {
    Product memory new_Product = Product(_name, _id);
    product1.push(new_Product);

        uint productId = product1.length;
        product1.push(new_Product);
        productToOwner[productId] = msg.sender;
        ownerProductCount[msg.sender]++;
        emit New_Product(productId, _name, _id);
    }

    function _generateRandomId(string memory _str) private view returns (uint) {
        uint rand = uint(keccak256(abi.encodePacked(_str)));
        return rand % idModulus;
    }
    

    function Ownership(uint _productId) public {
        productToOwner[_productId] = msg.sender;
        ownerProductCount[msg.sender]++;
    }


    function getProductsByOwner(address _owner) external view returns (uint[] memory) {
        uint counter = 0;
        uint[] memory result = new uint[](ownerProductCount[_owner]);
        for (uint i = 0; i < product1.length; i++) {
            if (productToOwner[i] == _owner) {
                result[counter] = i;
                counter++;
            }
        }
        return result;
    }

    modifier olderThan(uint _userId, uint _age) {
        require(_age >= 18, "Should be more than that age");
        _;
    }

    function validationUsers(uint _userId) public view olderThan(18, _userId) {
    }
}