package com.git.configserverdemo;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.config.server.EnableConfigServer;
import org.springframework.cloud.netflix.eureka.EnableEurekaClient;

/*
    /{application}/{profile}[/{label}]
    /{application}-{profile}.yml
    /{label}/{application}-{profile}.yml
    /{application}-{profile}.properties
    /{label}/{application}-{profile}.properties

 */
@EnableConfigServer
@SpringBootApplication
@EnableEurekaClient
public class ServiceConfigServerApplication {

    public static void main(String[] args) {
        SpringApplication.run(ServiceConfigServerApplication.class, args);
    }

}
