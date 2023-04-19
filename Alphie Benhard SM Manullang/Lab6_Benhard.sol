//SPDX-License-Identifier: GLP-3.0
//Exercise 1
pragma solidity >=0.5.0 <0.8.0;

//Exercise 2 
contract Factory { 
    uint idDigits=16;

    //Exercise 3
    uint idModulus=10^idDigits;

    //Exercise 4
    struct Product {
        string name;
        uint id;
    }
    //Exercise 5
    Product[] public products;

    //Exercise 6
    function _createProduct(string memory _name, uint _id) private {
        products.push(Product(_name,_id));
        uint productId= (products.length - 1);
        emit NewProduct(productId,_name,_id); 
    }

    //Exercise 7 
    function _generateRandomId(string memory _str) private view returns(uint) {
        //Exercise 8
        uint rand=uint(keccak256(abi.encodePacked(_str)));
        return (rand%idModulus);
    } 

    function createRandomProduct(string memory _name) public {
        uint randId=_generateRandomId(_name);
        _createProduct(_name, randId);
    } 

    //Exercise 9
    event NewProduct (uint ArrayProductId,  string name, uint id);
 
    //Exercise 10
    mapping (uint => address) public productToOwner;
    mapping (address => uint) ownerProductCount;

    //Exercise 11
    function _Ownership (uint _productId) private { 
        productToOwner[_productId] = msg.sender;
        ownerProductCount[msg.sender]++;
    }

    //Exercise 12
    function getProductsByOwner (address _owner) external view returns(uint[] memory) { 
        uint counter=0;
        uint[] memory result= new uint[](ownerProductCount[_owner]);
        for (uint i=0; i<products.length; i++) {
            if (productToOwner[i]==_owner) {
                result[counter]=i;
                counter++;
            }
        }
        return result;              
    }

    mapping (uint => uint) public age; 

    modifier olderThan (uint _age, uint _userId) {
        require (age[_userId] >= _age, "You Must Be At Least 18 Years Old");
        _;
    }
    
    //Exercise 13 - Checking OpenZeppelin Solidity Library

    //Exercise 14
    function validationUsers (uint _userId) public olderThan(18, _userId) {
    }

}
    ////Exercise 15(Wrap-up)
