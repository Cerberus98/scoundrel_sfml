Thoughts on hazard tiles:
-------------------------

  Say we jumped and landed on a vertical spike from the floor passable is still false.
  After the input phase, do a handle_environment() call In that call, we'd check what all 
  the tiles we touch. For each tile, call action, passing the player in at the end of the loop,
  check the player state. This would likely all happen after the ai as run, as well. This could
  easily all happen in this check. Maybe later, we push all relevant collided tiles into a vector
  and resolve all actions simultaneously.

  Now say we jumped horizontally into a spike sticking out from a wall. Then the above
  mechanism of pushing relevant tiles into an events vector to be resolved later is 
  even more helpful.

  Something else to consider is we wouldn't want to penalize the player twice if they managed to
  land between tiles on adjacent rows of spikes. As such, I think it's a better idea to collide
  all tiles the player is in contact with when moving but only resolve one of them as damage. In any
  given scenario, we shouldn't place differing types of hazards near one another. As an example,
  spikes inside of lava is confusing, so only choose one hazard or another.

Thoughts on player damage:
-------------------------
  Temporary invicibility is probably ideal, as otherwise you run the risk of getting juggled by
  hazards and enemies. However, for an event in which two things would damage the player at the exact
  same time, only one will resolve. Said resolution is entirely dependent on the order of the entity
  in the active entity list.
