package com.git.ribbondemo.com.git.service;

import com.netflix.hystrix.contrib.javanica.annotation.HystrixCommand;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

@Service
public class HelloService {
    @Autowired
    RestTemplate restTemplate;

    @HystrixCommand(fallbackMethod = "hiError")
    public String hiService(String name) {
        // 调用 get 请求，去 Service-SAYHI(当前有 2 个), 会做负载分发
        return restTemplate.getForObject("http://SAYHISERVICE/hi?name=" + name, String.class);
    }

    public  String hiError(String name){
        return "hi" + name + ", sorry error.";
    }
}
