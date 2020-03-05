package com.git.streamconsumerdemo;

import org.springframework.cloud.stream.annotation.EnableBinding;
import org.springframework.cloud.stream.annotation.StreamListener;

@EnableBinding(HelloBinding.class)
public class HelloListener {

    @StreamListener(target = HelloBinding.GREETING)
    public void processHelloChannelGreeting(String msg) {
        System.out.println("Consumer.\n");
        System.out.println(msg);
    }
}
