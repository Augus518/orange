echo %1\signtool sign /v /ac "%1\sign.cer" /n REDSTONE /d "%3" /t http://timestamp.verisign.com/scripts/timstamp.dll "%2"
%1\signtool sign /debug /v /ac "%1\sign.cer" /n REDSTONE /d "%3" /t http://timestamp.verisign.com/scripts/timstamp.dll "%2"