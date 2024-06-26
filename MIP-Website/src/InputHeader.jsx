import { useState } from "react";


function InputHeader()
{

    let [query, setQuery] = useState(""); 
    let [work, setWork] = useState("");
    let [instruction, setInstruction] = useState("");
    
    // Function calls rest api
    const calculateInstruction =  async() => {
        
        try
        {
            let data  = await (await fetch(`https://mips-converter.com/MIPS/${query}` )).text();
            console.log(data) 
            data = JSON.parse(data);
            console.log(data.work.replace("\n", "\\\n")); 
            setInstruction(data.instruction);
            setWork(data.work); 
        }
        catch(error)
        {
            console.log(error.message); 
            setInstruction(error.message);
            setWork(error.message); 
        }
       
    }

    // set query
    function changeInstruction(event){
        setQuery(event.target.value); 
    }

    return(
        <header className="InputHeader">
            <h1 className="InputHeader-title">MIPS Converter</h1>
            <p>Enter an 8 digit hexa-decimal or 32 bit instruction and press the button to convert it into a MIPS instruction.</p>
            <input placeholder="eg: 0x00000000" onChange={changeInstruction}></input>
            <div className="ConvertSection">
            <button className="ConvertButton" onClick={calculateInstruction}>Convert</button>
            <p>Instruction: {instruction}</p>
            <p>Process:</p>
            <p >{work.split('\n').map(e => <p>{e} </p>)} </p>
            </div>
        </header>
    );
}

export default InputHeader; 
