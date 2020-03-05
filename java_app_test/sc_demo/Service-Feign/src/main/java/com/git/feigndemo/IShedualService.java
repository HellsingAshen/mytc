package com.git.feigndemo;

import com.git.feigndemo.com.git.feigndemo.controller.SchedualServiceSayHiHystric;
import org.springframework.cloud.openfeign.FeignClient;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;

@FeignClient(value="sayHiService", fallback = SchedualServiceSayHiHystric.class)
public interface IShedualService {
    @RequestMapping(value= "/hi", method = RequestMethod.GET)
    String SayHiFromClientOne(@RequestParam(value="name") String name);
}
