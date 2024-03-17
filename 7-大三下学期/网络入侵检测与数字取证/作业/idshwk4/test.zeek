event http_reply(c: connection, version: string, code: count, reason: string)
{
    SumStats::observe("count of resp",
                      SumStats::Key($host=c$id$orig_h),
                      SumStats::Observation($num=1));
    if (code == 404) {
        SumStats::observe("count of 404 resp",
                      SumStats::Key($host=c$id$orig_h),
                      SumStats::Observation($num=1));
        SumStats::observe("count of uni 404 resp",
                      SumStats::Key($host=c$id$orig_h),
                      SumStats::Observation($str=c$http$uri));
    }
}


event zeek_init()
{
    local r1 = SumStats::Reducer($stream="count of resp",
                                 $apply=set(SumStats::SUM));
    local r2 = SumStats::Reducer($stream="count of 404 resp",
                                 $apply=set(SumStats::SUM));
    local r3 = SumStats::Reducer($stream="count of uni 404 resp",
                                 $apply=set(SumStats::UNIQUE));
    SumStats::create([$name = "detect attacker through 404 resp",
                      $epoch = 10min,
                      $reducers = set(r1,r2,r3),
                      $epoch_result(ts: time, key: SumStats::Key, result: SumStats::Result) =
                        {
                            local ratio1 : double = result["count of 404 resp"]$sum / result["count of resp"]$sum;
                            local ratio2 : double = result["count of uni 404 resp"]$unique / result["count of 404 resp"]$sum;
                            if (result["count of 404 resp"]$sum > 2 && ratio1 > 0.2 && ratio2 > 0.5) {
                                print fmt("%s is a scanner with %.0f scan attemps on %.0f urls", key$host, result["count of 404 resp"]$sum, result["count of uni 404 resp"]$sum);
                            }
                        }]);
}
