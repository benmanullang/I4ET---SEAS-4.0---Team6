pragma solidity >=0.5.0 <0.9.0;

contract Factory {
    uint public constant idDigits = 16;
    uint public constant idModulus = 10;
    uint public constant des_duration = 30; // Projected Duration for total process

    struct Product {
        string name;
        uint id;
        uint price;
        string del_status;
        string inst_status;
        bool isPaid;
    }

    Product[] public products;
    uint public productId;
    address public productAddress;
    address payable public manufacturer;
    address payable public customer;

    constructor() {
        manufacturer = payable(msg.sender);
        customer = payable(msg.sender);
    }

    function createProduct(string memory _name, uint _price, string memory _del, string memory _inst) private  {
        uint _id = productId + 1; // Generate a unique ID for each product
        Product memory newProduct = Product({
            name: _name,
            id: _id,
            price: _price,
            del_status: _del,
            inst_status: _inst,
            isPaid: false
        });
        products.push(newProduct);
        productId = _id;
        productAddress = address(this);
    }

    // Product List
    function product_list() public {
        createProduct("Water Level Sensor", 300, "Not Delivered", "Not Installed");
        createProduct("RGB", 150, "Not Delivered", "Not Installed");
        createProduct("Pump", 300, "Not Delivered", "Not Installed");
        createProduct("Temperature Sensor", 150, "Not Delivered", "Not Installed");
    }

    function makePrePayment(uint _productId) public payable {
        require(_productId > 0 && _productId <= products.length, "Invalid product ID");
        Product storage product = products[_productId - 1];
        require(!product.isPaid, "Pre-payment already made for this product");
        uint prePaymentAmount = product.price * 30 / 100;
        require(msg.value >= prePaymentAmount, "Insufficient ether sent");
        product.isPaid = true;
        customer = payable(msg.sender);
    }
    function setDelivered(uint _productId) public {
        require(_productId > 0 && _productId <= products.length, "Invalid product ID");
        Product storage product = products[_productId - 1];
        require(product.isPaid, "Pre-payment not made for this product yet");
        require(keccak256(bytes(product.del_status)) == keccak256(bytes("Not Delivered")), "Product already delivered");
        product.del_status = "Delivered";
        uint paymentAmount = product.price * 30 / 100;
        manufacturer.transfer(paymentAmount);
        customer.transfer(paymentAmount);
    }

    function setInstalled(uint _productId) public {
        require(_productId > 0 && _productId <= products.length, "Invalid product ID");
        Product storage product = products[_productId - 1];
        require(product.isPaid, "Pre-payment not made for this product yet");
        require(keccak256(bytes(product.inst_status)) == keccak256(bytes("Not Installed")), "Product already installed");
        product.inst_status = "Installed";
        uint paymentAmount = product.price * 40 / 100;
        manufacturer.transfer(paymentAmount);
        customer.transfer(paymentAmount);
    }

    function bonus(uint _duration) public {
        require(_duration > 0, "Duration must be a positive integer");

        uint efficiency = des_duration * 100 / _duration;

        if (efficiency >= 100) {
            Product storage product = products[productId - 1];
            uint bonusAmount = product.price * (des_duration - _duration) * 10 / (des_duration * 3);
            manufacturer.transfer(bonusAmount);
        } 
        else {
            Product storage product = products[productId - 1];
            uint penaltyAmount = product.price * (_duration - des_duration) * 10 / _duration;
            manufacturer.transfer(penaltyAmount);
            uint paymentAmount = product.price * (100 - penaltyAmount * 2) / 100;
            customer.transfer(paymentAmount);
        }
}

    function getManufacturer() public view returns (address) {
        return manufacturer;
    }

    function getCustomer() public view returns (address) {
        return customer;
    }
}


