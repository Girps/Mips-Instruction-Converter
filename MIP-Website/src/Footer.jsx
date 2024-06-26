


function Footer()
{
    const imageUrl = 'https://github.com/Girps.png' ; 
    const githubUrl = "https://github.com/Girps/Mips-Instruction-Converter"; 
    const redirect = () => {
        window.location=githubUrl;  
        console.log("Clicked"); 
        }

    return (
        <footer className="specialFooter">
        <div> 
            <a href={githubUrl}>
          <img className="specialFooter-image"onClick={redirect} src={imageUrl}  ></img>
          </a>
        </div>
      <p>Webpage and REST api created by Jesse Jimenez click on profile picture for source code</p>
      </footer>
    ); 

}

export default Footer; 