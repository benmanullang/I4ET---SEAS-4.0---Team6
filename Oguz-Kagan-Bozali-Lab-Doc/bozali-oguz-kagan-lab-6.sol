pragma solidity >=0.5.0 <0.9.0; // Version choose as 0.9 instead of 0.8 because it does not compile with 0.8

contract Factory {
    uint public constant idDigits = 16;
    uint public constant idModulus = 10;
    
    struct Product {
        string name;
        uint id;
    }
    
    Product[] public products;
    uint public productId;
    address public productAddress;
    
    function createProduct(string memory _name, uint _id) private {
        Product memory newProduct = Product({
            name: _name,
            id: _id
        });
        productId = products.length;
        products.push(newProduct);
        productAddress = address(this);
        emit NewProduct(_name, _id, productId);
    }
      
    function _generateRandomId(string memory _str) private pure returns (uint) {
        return uint(keccak256(abi.encodePacked(_str))) % idModulus;
    }

    function createRandomProduct(string memory _name) public {
        uint randId = _generateRandomId(_name);
        createProduct(_name, randId);  
    }

    event NewProduct(string name, uint id, uint arrayProductId);

    mapping (address => address) public productToOwner;
    mapping (address => uint) public ownerProductCount;

    function Ownership() public {
        productToOwner[productAddress] = msg.sender;
        ownerProductCount[msg.sender]++;
    }

    function getProductsByOwner(address _owner) external view returns (uint[] memory) {
        uint counter = 0;
        uint[] memory result = new uint[](ownerProductCount[_owner]);
        for (uint i = 0; i < products.length; i++) {
            if (productToOwner[address(this)] == _owner) {
                result[counter] = i;
                counter++;
            }
        }
        return result;
    }

    modifier olderThan (uint _age, uint _userId) {
        require (_age >= 18, "Customer Over 18");
        _;
    }


    function validationUsers (uint _userId) public olderThan(18, _userId) {
    }

}
