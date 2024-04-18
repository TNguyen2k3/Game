var http = require('http');
var server = http.createServer();
var socketIO = require('socket.io');
var io = socketIO(server, {allowEIO3: true});
var num_clients = 0;
var turn = 1;
var finished = false;
var matrix = [];
// tạo mảng với số phần tử là chiều rộng màn hình / 20 * chiều dài màn hình / 20
var a = 51, b = 41;
for (var i = 0; i < 51; i++) {
    matrix[i] = new Array(41);
}


for (var i = 0; i < 51; i++) {
    for (var j = 0; j < 41; j++){
        matrix[i][j] = 0;
    }
}

for (var i = 0; i < 10; i++) {
    for (var j = 0; j < b; ++j) {
        matrix[i][j] = 3;
    }
}
for (var i = a - 10; i < a; i++) {
    for (var j = 0; j < b; ++j) {
        matrix[i][j] = 3;
    }
}
for (var i = 0; i < a; ++i) {
    for (var j = 0; j < 10; j++) {
        matrix[i][j] = 3;
    }
}
for (var i = 0; i < a; ++i) {
    for (var j = b - 10; j < b; j++)
        matrix[i][j] = 3;
}
function checkDraw(matrix, rows, cols){
    for(var i = 10; i < a - 10; i++) {
        for (var j = 10; j < b - 10; j++) {
            if (matrix[i][j] == 0 || matrix[i][j] == 3) {
                return false;
            }
        }
    }
    return true;
}
// check điều kiện thắng
function checkWin(matrix, rows, cols, player) {
    // Kiểm tra hàng
    for (var i = 0; i < rows; i++) {
        for (var j = 0; j <= cols - 5; j++) {
            var count = 0;
            for (var k = 0; k < 5; k++) {
                if (matrix[i][j + k] == player) {
                    count++;
                } else {
                    count = 0;
                    break;
                }
            }
            if (count == 5) {
                return true;
            }
        }
    }

    // Kiểm tra cột
    for (var i = 0; i < cols; i++) {
        for (var j = 0; j <= rows - 5; j++) {
            var count = 0;
            for (var k = 0; k < 5; k++) {
                if (matrix[j + k][i] == player) {
                    count++;
                } else {
                    count = 0;
                    break;
                }
            }
            if (count == 5) {
                return true;
            }
        }
    }

    // Kiểm tra đường chéo chính
    for (var i = 0; i <= rows - 5; i++) {
        for (var j = 0; j <= cols - 5; j++) {
            var count = 0;
            for (var k = 0; k < 5; k++) {
                if (matrix[i + k][j + k] == player) {
                    count++;
                } else {
                    count = 0;
                    break;
                }
            }
            if (count == 5) {
                return true;
            }
        }
    }

    // Kiểm tra đường chéo phụ
    for (var i = 4; i < rows; i++) {
        for (var j = 0; j <= cols - 5; j++) {
            var count = 0;
            for (var k = 0; k < 5; k++) {
                if (matrix[i - k][j + k] == player) {
                    count++;
                } else {
                    count = 0;
                    break;
                }
            }
            if (count == 5) {
                return true;
            }
        }
    }

    return false;
}

// Sử dụng hàm checkWin để kiểm tra điều kiện thắng với player là giá trị 1 hoặc 2


/* 1: X
   0: O
*/
let clients = {};
clients[0] = "";
clients[1] = "";
function swapturn(turn){
    if(turn == 1){
        turn = 0;
        // X
    }
    else{
        turn = 1;
        // O
    }
    return turn;
}

io.on('connection', function(socket) {
    finished = false;
    console.log("Number of clients before connecting:" + num_clients);
    console.log('A client connected: ' + socket.id);
    for(var i = 0; i < 2; i++){
        if (clients[i] == ""){
            clients[i] = socket.id;
            break;
        }
    }
    num_clients++;
    console.log("Number of clients after connecting:" + num_clients);
    for (var i = 0; i < 2; i++){

        console.log(i + ": " + clients[i]);

    }
    
    // if (num_clients === 1){
    //     console.log("Waiting for opponent");
        
    //     io.emit('hello', "Waiting for opponent");
    // }
    // else {
        
    if (num_clients === 2)   {
        io.emit('hello', "Start");
        io.emit('hello', "init turn: " + turn.toString());
    
    
        if (io.to(clients[0]).emit('you', "You are X") ) console.log(clients[0]+ "You are X");
        else console.log("Failed to send turn to client");
        if (io.to(clients[1]).emit('you', "You are O") ) console.log(clients[1] + "You are O");
        else console.log("Failed to send turn to client");
    }  
    // Xử lý sự kiện 'Hello' từ máy khách
    socket.on('solo', function(data){
        // if (data == null) console.log("A null data");
        

        console.log("Is finished game:" + finished);
        // Gửi dữ liệu nhận được từ một máy khách đến tất cả các máy khách khác
        
        if (data[11] == turn) {
            
            // Phân tích chuỗi JSON thành một mảng các đối tượng JavaScript
            var jsonArray = JSON.parse(data);

            // Lấy giá trị của thuộc tính "value" từ đối tượng JSON
            var valueString = jsonArray[0].value;

            // Tách chuỗi thành các số bằng cách sử dụng phương thức split
            var numbers = valueString.split(' ');

            // Chuyển đổi các chuỗi số thành số nguyên
            var number1 = parseInt(numbers[0]);
            var number2 = parseInt(numbers[1]);
            var number3 = parseInt(numbers[2]);
            if (matrix[number2][number3] == 0){
                if (number1 == 1) {
                    matrix[number2][number3] = 1;
                }
                else if (number1 == 0) {
                    matrix[number2][number3] = 2;
                }
            }
            
            // console.log(number1); // In ra: 1
            // console.log(number2); // In ra: 22
            // console.log(number3); // In ra: 21
            // console.log(data);
            io.emit('solo', data);
            turn = swapturn(turn);

            // in ma trận
            // for (var i = 0; i < 51; i++) {
            //     var rowString = '';
            //     for (var j = 0; j < 41; j++) {
            //         rowString += matrix[i][j]; // Thêm giá trị phần tử vào chuỗi
            //         if (j < 41 - 1) {
            //             rowString += ' '; // Cách nhau bằng dấu cách
            //             // Hoặc rowString += ', '; // Cách nhau bằng dấu phẩy
            //         }
            //     }
            //     // console.log(rowString); // In hàng
            // }

            var player1Win = checkWin(matrix, 51, 41, 1);
            var player2Win = checkWin(matrix, 51, 41, 2);
            if (checkDraw(matrix, 51, 41)){
                io.emit('result', "end_game");
                io.emit('result', "Draw");
            }
            if (player1Win || player2Win){
                io.emit('result', "end_game");
                
            }
            if (player2Win){
                io.emit('result', "O win");
                
                for (var i = 11; i < 40; i++) {
                    for (var j = 11; j < 30; j++){
                        matrix[i][j] = 0;
                    }
                }
                console.log("O Win");
                
                
            }
            else if (player1Win){
                io.emit('result', "X win");
                
                for (var i = 11; i < 40; i++) {
                    for (var j = 11; j < 30; j++){
                        matrix[i][j] = 0;
                    }
                }
                console.log("X Win");
                
            }
            if (player1Win || player2Win || checkDraw(matrix, 51, 41)){
                finished = true;
                socket.disconnect(true);
                console.log("The reason end game: The game has finished");
                
                for (var i = 1; i >= 0; i--){
                    console.log("Number of clients connected:" + num_clients);
                    if (clients[i] !== "") {
                        console.log('A client disconnected.' + clients[i]);
                        clients[i] = "";
                        num_clients--;
                    }
                    
                }  
                    
            } 
                for (var i = 0; i < 2; i++){

                    console.log(i + ": " + clients[i]);
        
                }
                
            
            
            
        }
    });
        
    //}

    // Xử lý sự kiện ngắt kết nối từ máy khách
    // socket.on('disconnect', function() {
    //     console.log("The reason end game: A client was disconnected");
    //     io.emit('result', "end_game");
    //     if (socket.id == clients[0] && !finished){
    //         io.emit('result', "O win");
    //     }
    //     else if (socket.id == clients[1]  && !finished){
    //         io.emit('result', "X win");
    //     }
        
    //     socket.disconnect(true);
    //     console.log("The game has finished");
    //     if (!finished){
    //         for (var i = 1; i >= 0; i--){
    //             console.log("Number of clients connected:" + num_clients);
    //             if (clients[i] == socket.id) {
    //                 console.log('A client disconnected.' + clients[i]);
    //                 clients[i] = "";
    //                 num_clients--;
    //             }
                
    //         }  
    //     }
        
    //     io.close();
    //     // socket.disconnect(true);
    //     for (var i = 0; i < 2; i++){

    //         console.log(i + ": " + clients[i]);

    //     }
    //     finished = false;
        
        
        
        
        
    // });
    socket.on('disconnect', function() {
        console.log("A client was disconnected: " + socket.id);
    
        // Kiểm tra xem client đang ngắt kết nối có phải là client nào không
        if (!finished) {
            // Xóa client đã ngắt kết nối khỏi danh sách clients
            if (socket.id === clients[0]) {
                clients[0] = "";
            } else if (socket.id === clients[1]) {
                clients[1] = "";
            }
    
            // Giảm số lượng người chơi đi 1
            num_clients--;
    
            console.log("Number of remaining clients: " + num_clients);
    
            // Kiểm tra nếu trò chơi đã kết thúc và không còn client nào kết nối
            if (finished && num_clients === 0) {
                console.log("All clients disconnected after game over");
                // Thực hiện hành động chuyển scene hoặc các hành động khác
                // ở đây, bạn có thể gọi các hàm hoặc thực hiện các thao tác cần thiết
    
                // Gửi thông điệp kết thúc trò chơi cho tất cả client
                io.emit('game_over', "Game over!");
    
                // Ngắt kết nối tất cả các client
                io.close();
            } else if (finished && num_clients === 1) {
                // Nếu chỉ còn một client còn kết nối và trò chơi đã kết thúc
                // Gửi thông điệp cho client còn lại về việc họ là người chiến thắng
                let remainingClient = (clients[0] !== "") ? clients[0] : clients[1];
                if (remainingClient !== "") {
                    io.to(remainingClient).emit('result', "You win!");
                    console.log("Client " + remainingClient + " wins!");
                } else {
                    console.log("No remaining client.");
                }
    
                // Thực hiện hành động chuyển scene hoặc các hành động khác
                // ở đây, bạn có thể gọi các hàm hoặc thực hiện các thao tác cần thiết
    
                // Ngắt kết nối client
                socket.disconnect(true);
            }
        } else {
            console.log("Disconnected client is not in the clients list.");
        }
        
    });
});

server.listen(8888, function(){
    console.log('Server is running on port 8888');
    
});