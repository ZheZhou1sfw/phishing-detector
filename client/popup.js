chrome.tabs.query({active: true, currentWindow:true}, function(tabs)
{
    // step 1: get the url
    let url = tabs[0].url;
    // step 2: perform checks

    // navigator.tcpPermission.requestPermission({remoteAddress:"24.125.126.126", remotePort:44444}).then(
    //     () => {
    //         // Permission was granted
    //         // Create a new TCP client socket and connect to remote host
    //         var mySocket = new TCPSocket("24.125.126.12", 44444);
    //
    //         // Send data to server
    //         mySocket.writeable.write("google.com").then(
    //             () => {
    //
    //                 // Data sent sucessfully, wait for response
    //                 console.log("Data has been sent to server");
    //                 mySocket.readable.getReader().read().then(
    //                     ({ value, done }) => {
    //                         if (!done) {
    //                             // Response received, log it:
    //                             console.log("Data received from server:" + value);
    //                         }
    //
    //                         // Close the TCP connection
    //                         mySocket.close();
    //                     }
    //                 );
    //             },
    //             e => console.error("Sending error: ", e)
    //         );
    //     }
    // );

    // const net = require('net');
    //
    // const client = new net.Socket();
    // client.connect({ port: 44444 }, "24.125.126.126", () => {
    //     client.write(`google.com`);
    // });
    // client.on('data', (data) => {
    //     console.log(`Server says: ${data.toString('utf-8')}`);
    //     client.destroy();
    // });

    // chrome.sockets.tcp.create({}, function() {
    //     chrome.sockets.tcp.connect(200,
    //         "24.125.126.126", 44444, (info) => {
    //         console.log(info);
    //         console.log('connected');
    //         });
    // });


    // step 3: render result

    document.getElementById("level").innerHTML = url;
});


