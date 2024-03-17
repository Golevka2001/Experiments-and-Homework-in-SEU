# idshwk4

#### 介绍
上传 *test.zeek* 文件

#### 要求
    Detection Requiremet:
        · detect http scan based on 404 response
    Algorithm Requirement:
        · make 404 statistics on orig_h
        In every 10 minutes
        · if the count of 404 response > 2
        · and if the 404 ratio > 20% (404 ratio = 404 response/all response)
        · and if (the unique count of url response 404 / if the count of 404 response ) > 0.5
        · then output "x.x.x.x is a scanner with y scan attemps on z urls" where
            x.x.x.x is the orig_h, y is the count of 404 response, z is the unique count of url response 404