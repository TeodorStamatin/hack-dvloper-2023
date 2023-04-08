import React from "react";

export default function Chatbox(props) {
    const [chat, setChat] = React.useState(
        [
            {userId: 1, text: "Hello"},
            {userId: 1, text: "World"},
            {userId: 2, text: "How"},
            {userId: 1, text: "Are"},
            {userId: 2, text: "You"},
            {userId: 1, text: "Today"},
            {userId: 2, text: "I"},
            {userId: 2, text: "Am"},
            {userId: 2, text: "Fine"},
            {userId: 1, text: "Good"},
            {userId: 1, text: "To"},
            {userId: 1, text: "Hear"},
        ]);

  return (
    <div className="chatBox">
        <div className="messageBox">
        {chat.map((message, index) => (
            <div key={index} className={`message ${props.userId === message.userId ? "myMessage" : "otherMessage"}`}>
                {message.text}
            </div>
        ))}
      </div>
      <input placeholder="Write..."></input>
    </div>
  );
}