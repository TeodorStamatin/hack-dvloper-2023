import React from "react";
import { useState, useRef, useEffect } from "react";

export default function Chatbox(props) {
    const [message, setMessage] = useState("");
    const [chat, setChat] = useState(
        [
            {userColor: "white", text: "Hello"},
            {userColor: "white", text: "World"},
            {userColor: "black", text: "How"},
            {userColor: "white", text: "Are"},
            {userColor: "black", text: "You"},
            {userColor: "white", text: "Today"},
            {userColor: "black", text: "I"},
            {userColor: "black", text: "Am"},
            {userColor: "black", text: "Fine"},
            {userColor: "white", text: "Good"},
            {userColor: "white", text: "To"},
            {userColor: "white", text: "Hear"},
        ]);

    function handleKeyPress(event) {
        if (event.key === "Enter") {
            if (message === "") return;
            setChat([...chat, {userColor: props.userColor, text: message}]);
            setMessage("");
        }
    }
    const bottomRef = useRef();
    useEffect(() => {
        console.log("scrolling");
        bottomRef.current?.scrollIntoView({behavior: 'smooth'});
      }, [chat]);

  return (
    <div className="chatBox">
        <div className="messageBox">
        {chat.map((message, index) => (
            <div key={index} className={`message ${props.userColor === message.userColor ? "myMessage" : "otherMessage"}`}>
                {message.text}
            </div>
        ))}
        <div ref={bottomRef}></div>
      </div>
      <input placeholder="Write..." value={message}
            onChange={(event) => setMessage(event.target.value)}
            onKeyPress={(event) => handleKeyPress(event)}></input>
    </div>
  );
}