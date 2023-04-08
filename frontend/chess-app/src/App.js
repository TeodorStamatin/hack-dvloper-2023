import './App.css';

import { useState } from "react";

import Chessboard from './components/Chessboard';
import History from './components/History';

function App() {
  const [history, setHistory] = useState([
    {pieceType: "WHITE PAWN", from: "A1", to: "A2"},
  ]);

  return (
    <div className="App">
      <header className="App-header">
        <h1>The Black Sheep | Chess Engine</h1>
        <Chessboard history={history} setHistory={setHistory} />
        <History history={history} setHistory={setHistory} />
      </header>
    </div>
  );
}

export default App;
