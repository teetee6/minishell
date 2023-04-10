# minishell
# the order in implementation
1. show prompt
2. make history
3. lexing into tokens
4. make ASTree from tokens
5. execute ASTree
6. handling signal

```mermaid
flowchart TB
 subgraph printPrompt
   Prompt
 end
 subgraph EXIT
   exit[delete all and exit]
 end
 
 subgraph makeHistory
   History[(new History)] --> input
   input{enter EOF?} -->|YES| exit
   input -->|NO| input2
   input2{enter newline?} -->|YES| check_input
   check_input{check if \n input is empty \n or all whitespace}
   check_input --> |YES| DelHistory[delete current history]
   DelHistory --> Prompt
   input2 -->|NO| input3
   input3{is up and down?} -->|YES| retr_hist
   retr_hist[retrieve previously saved History data \n if possible]
   input3 -->|NO| save_onech[if printable, concatenate.\n if del key, delete one letter]
   retr_hist --> input
   save_onech --> input
   check_input --> |NO| SaveHistory[(save current history)]
 end
 subgraph LEXER
   check_quote{check quote is well closed}
   check_quote -->|NO| exit
   check_quote --> tokenize
   tokenize[(tokenize)] --> replace_env[(replace_env)] --> strip_quotes[(strip_quotes)]
   tokenize --> |SYNTAX_ERROR| exit
   replace_env --> |SYNTAX_ERROR| exit
   strip_quotes --> |SYNTAX_ERROR| exit
 end
 subgraph AST
   subgraph job_recur
    
	   job{has pipe?}
	   job -->|YES| job1
	   cmd --- job1
	   job1 -->|recursive| job
	   job -->|NO| cmd2
   end
   append_redirs[append redirs first]
   append_simplecmd[append cmd and args]
   append_redirs --> append_simplecmd
   cmd --> append_redirs
   cmd2 --> append_redirs
   job_recur --> astnode
 end
 astnode --> execute
  
  style Prompt fill:#3567F3
  style exit fill:#CE2642
  style execute fill:#3567F3
  Prompt --> History
  SaveHistory --> check_quote
  strip_quotes --> job
  
```

1. lexer - 평문을 ' ', '<', '<<', '>', '>>', '|' 에 나눠 토큰화한다. 토큰화 과정 중에 큰 따옴표 혹은 평문 내의 환경변수를 환경변수 값으로 치환한다.
