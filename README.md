# lexer parser by Salim Regragui
A basic text game lexer and parser made in c language. This lexer/parser doesn't have the pretention of competing against the big wolfs of the domain
but is rather just a learning project for me.

Feel free to use this code for your project or change it :)

# Example of how the parser works

- User : go to the store and then get beer from fridge and then go to the cashier and than take wallet from pocket and then look down.

- Lexer transfrom phrase into : "go store","get beer from fridge","go cashier","take wallet from pocket","look down"

The lexer then sends these tokens that it created to the parser.

- Parser outputs: - You wanna go to the store.
                  - Then you wanna get the beer from the fridge.
                  - Then you wanna go to the cashier.
				  - Then you wanna take your wallet from your pocket.
				  - Then you wanna look down.
				  
As you can see the lexer/parser does it's job but at the moment it's pretty basic, currently working on making it more intelligent.