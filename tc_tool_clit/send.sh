#! /bin/ksh

for i in `seq 1`
do 
   
#echo $i>>sendsh.log

 ./tool_sndc -port "8000" -ip "192.168.91.128" -data "<Transaction><Header><sysHeader><msgId>00420180702094129001909399</msgId><msgDate>2018-07-02</msgDate><msgTime>09:41:29.824</msgTime><globalSq>00420180702020001909399001000000</globalSq><servCd>R01101006439</servCd><operation/><tranCode>C105</tranCode><sysCd>004</sysCd><serverCd/><bizId>C105</bizId><bizType>C105</bizType><orgCd>3401010003</orgCd><termCd>10.2.155.40=</termCd><resCd/><resText/><bizResCd/><bizResText/><authId/><authPara/><authContext/><pinIndex/><pinValue/><extend/></sysHeader></Header><Body><request><bizHeader><I1SBNO>3401010003</I1SBNO><I1USID>000303</I1USID><I1AUUS/><I1AUPS/><I1WSNO>11111111</I1WSNO></bizHeader><bizBody><RESOLVE_TYPE>3</RESOLVE_TYPE><ECIF_CUST_NO>200100014386</ECIF_CUST_NO><CERT_TYPE/><CERT_NO/><PARTY_NAME/><OPEN_CERT_FLAG/><List/><FIRST_NO/><RESULT_SIZE/><ADDR_DESC_FLAG/></bizBody></request></Body></Transaction>" -lencode "hex">>sendsh.log 

done 

