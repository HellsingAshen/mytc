sleep 2;
rabbitmqctl eval 'rabbit_amqqueue:declare({resource, <<"/">>, queue, <<"scpServiceLog">>}, true, false, [], none).';
sleep 2;
rabbitmqctl eval 'rabbit_amqqueue:declare({resource, <<"/">>, queue, <<"scpTransLog">>}, true, false, [], none).';
