package com.git.demo;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.netflix.eureka.EnableEurekaClient;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@EnableEurekaClient
@RestController
@SpringBootApplication
public class SayHiServiceApplication {

    public static void main(String[] args) {
        SpringApplication.run(SayHiServiceApplication.class, args);
    }
    @Value("${server.port}")
    String port;

    @RequestMapping("/hi")
    public String sayHi(@RequestParam String name){
        return "hi "+name+",i am from port:" +port;
    }

    @RequestMapping("/think")
    public String sayThink(){
        return "hi "+", I'm thinking.";
    }

}
