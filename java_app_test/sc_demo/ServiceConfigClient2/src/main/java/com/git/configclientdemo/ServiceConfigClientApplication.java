package com.git.configclientdemo;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.context.config.annotation.RefreshScope;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/*
    test --  rabbitmq send msg to configclient2 and configclient2 do refresh op
 */
@RestController
@RefreshScope
@SpringBootApplication
public class ServiceConfigClientApplication {

    public static void main(String[] args) {
        SpringApplication.run(ServiceConfigClientApplication.class, args);
    }

    @Value("${foo}")
    String foo;

    @RequestMapping(value = "/hi")
    public String hi(){
        return foo;
    }
}

